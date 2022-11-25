import {
  FETCH_PHOTO_URLS,
  PHOTOS_DELETE,
  PHOTO_UPLOAD_FINISH,
  PHOTO_UPLOAD_START,
  PHOTO_UPLOAD_PROGRESS,
} from '../actions/';

export default (
  state = {
    urls: [],
    uploading: false,
    progress: 0,
  },
  action
) => {
  switch (action.type) {
    case FETCH_PHOTO_URLS:
      return {
        ...state,
        urls: action.urls,
      };
    case PHOTOS_DELETE:
      return {
        ...state,
        urls: [],
      };
    case PHOTO_UPLOAD_START:
      return {
        ...state,
        uploading: true,
      };
    case PHOTO_UPLOAD_FINISH:
      return {
        ...state,
        progress: 0,
        uploading: false,
      };
    case PHOTO_UPLOAD_PROGRESS:
      return {
        ...state,
        progress: state.progress + action.progress,
      };
    default:
      return state;
  }
};
