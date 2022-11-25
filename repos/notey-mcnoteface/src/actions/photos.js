import { storage, storageRef } from '../firebase/';

export const FETCH_PHOTO_URLS = 'FETCH_PHOTO_URLS';

export const PHOTOS_DELETE = 'PHOTOS_DELETE';

export const PHOTO_UPLOAD_START = 'PHOTO_UPLOAD_START';
export const PHOTO_UPLOAD_FINISH = 'PHOTO_UPLOAD_FINISH';
export const PHOTO_UPLOAD_PROGRESS = 'PHOTO_UPLOAD_PROGRESS';

const photoUrlsFetch = (urls) => {
  return {
    type: FETCH_PHOTO_URLS,
    urls: urls,
  };
};

const photosDelete = () => {
  return {
    type: PHOTOS_DELETE,
  };
};

const photoUploadStart = () => {
  return {
    type: PHOTO_UPLOAD_START,
  };
};

const photoUploadFinish = () => {
  return {
    type: PHOTO_UPLOAD_FINISH,
  };
};

const photoUploadProgress = (progress) => {
  return {
    type: PHOTO_UPLOAD_PROGRESS,
    progress: progress,
  };
};

export const uploadNotePhotos = (photos) => (dispatch, getState) => {
  const state = getState();
  const currentRef = storageRef
    .child('user')
    .child(state.auth.user.uid)
    .child('note')
    .child(state.notes.currentNote.id);
  const incrementAmount = 100 / photos.length;

  dispatch(photoUploadStart());

  Promise.all(
    photos.map((photo) => {
      return currentRef
        .child(photo.name)
        .put(photo)
        .then((_) => {
          console.log('An Upload Completed: ', photo.name);
          dispatch(photoUploadProgress(incrementAmount));
        })
        .catch((error) => {
          console.log('Failed to upload file: ', error);
        });
    })
  )
    .then((_) => {
      console.log('All Files Uploaded!');
      dispatch(photoUploadFinish());
    })
    .catch((error) => {
      console.log('Some Uploads Failed: ', error.message);
    });
};

export const deleteAssociatedPhotos = (photoUrls) => (dispatch) => {
  dispatch(photosDelete());

  photoUrls.forEach((url) => {
    storage
      .refFromURL(url)
      .delete()
      .then(console.log('File Deleted!'))
      .catch((error) => {
        console.log('Failed to delete photo: ', error);
      });
  });
};

export const fetchNotePhotos = () => (dispatch, getState) => {
  const state = getState();
  const currentRef = storageRef
    .child('user')
    .child(state.auth.user.uid)
    .child('note')
    .child(state.notes.currentNote.id);

  currentRef
    .listAll()
    .then((photos) => {
      Promise.all(
        photos.items.map((photo) => {
          return photo.getDownloadURL();
        })
      ).then((photoUrls) => {
        dispatch(photoUrlsFetch(photoUrls));
      });
    })
    .catch((error) => {
      console.log('Error Fetching Photo URLS: ', error);
    });
};
