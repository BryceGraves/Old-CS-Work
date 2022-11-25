import { db, extractAndStoreData } from '../firebase/';

export const NOTE_CREATE = 'NOTE_CREATE';
export const NOTE_UPDATE = 'NOTE_UPDATE';
export const NOTE_DELETE = 'NOTE_DELETE';
export const NOTE_SET = 'NOTE_SET';

export const NOTE_CATEGORY_CREATE = 'NOTE_CATEGORY_CREATE';

export const NOTES_DATA_FETCH = 'NOTES_DATA_FETCH';

const noteCreate = (categoryId, note) => {
  return {
    type: NOTE_CREATE,
    note: note,
    categoryId: categoryId,
  };
};

const noteCategoryCreate = (categoryId, name) => {
  return {
    type: NOTE_CATEGORY_CREATE,
    categoryId: categoryId,
    name: name,
  };
};

const noteUpdate = () => {
  return {
    type: NOTE_UPDATE,
  };
};

const noteDelete = (categoryId, noteId) => {
  return {
    type: NOTE_DELETE,
    noteId: noteId,
    categoryId: categoryId,
  };
};

const noteSet = (categoryId, note) => {
  return {
    type: NOTE_SET,
    note: note,
    categoryId: categoryId,
  };
};

const notesDataFetch = (data) => {
  return {
    type: NOTES_DATA_FETCH,
    data: data,
  };
};

export const createNote = (userId, categoryId, title, content) => (dispatch) => {
  db.collection('users')
    .doc(userId)
    .collection('categories')
    .doc(categoryId)
    .collection('notes')
    .add({
      title: title,
      content: content,
    })
    .then((noteRef) => {
      console.log('Note written with ID: ', noteRef.id);
      dispatch(
        noteCreate(categoryId, {
          id: noteRef.id,
          title: title,
          content: content,
        })
      );
    })
    .catch((error) => {
      console.error('Error adding note: ', error);
    });
};

export const createNoteCategory = (userId, category) => (dispatch) => {
  db.collection('users')
    .doc(userId)
    .collection('categories')
    .add({ name: category })
    .then((categoryRef) => {
      console.log('Category written with ID: ', categoryRef.id);
      dispatch(noteCategoryCreate(categoryRef.id, category));
    })
    .catch((error) => {
      console.error('Error adding note: ', error);
    });
};

export const updateNote = () => (_, getState) => {
  const state = getState();

  db.collection('users')
    .doc(state.auth.user.uid)
    .collection('categories')
    .doc(state.notes.currentCategory)
    .collection('notes')
    .doc(state.notes.currentNote.id)
    .update({
      title: state.notes.currentNote.title,
      content: state.notes.currentNote.content,
    })
    .then(function() {
      console.log('Note successfully updated!');
    })
    .catch(function(error) {
      console.error('Error updating note: ', error);
    });
};

export const deleteNote = () => (dispatch, getState) => {
  const state = getState();

  db.collection('users')
    .doc(state.auth.user.uid)
    .collection('categories')
    .doc(state.notes.currentCategory)
    .collection('notes')
    .doc(state.notes.currentNote.id)
    .delete()
    .then(function() {
      console.log('Note successfully deleted!');
      dispatch(noteDelete(state.notes.currentCategory, state.notes.currentNote.id));
    })
    .catch(function(error) {
      console.error('Error deleting note: ', error);
    });
};

export const setNote = (categoryId, note) => (dispatch) => {
  dispatch(noteSet(categoryId, note));
};

export const fetchNotes = (userId) => (dispatch) => {
  const userCategoryRef = db
    .collection('users')
    .doc(userId)
    .collection('categories');

  userCategoryRef
    .get()
    .then((userCategories) => {
      dispatch(extractAndStoreData(userCategoryRef, userCategories, notesDataFetch));
    })
    .catch((error) => {
      console.log('Failed fetching user notes: ', error);
    });
};
