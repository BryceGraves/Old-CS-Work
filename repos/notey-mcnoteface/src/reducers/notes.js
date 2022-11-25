import {
  NOTE_CREATE,
  NOTE_UPDATE,
  NOTE_DELETE,
  NOTE_SET,
  NOTE_CATEGORY_CREATE,
  NOTES_DATA_FETCH,
} from '../actions/';

export default (
  state = {
    currentNote: null,
    currentCategory: null,
    categories: {},
  },
  action
) => {
  switch (action.type) {
    case NOTE_CREATE:
      // TODO: move random filler chaff into here it shouldn't be in the damn component
      return {
        ...state,
        categories: {
          ...state.categories,
          [action.categoryId]: {
            ...state.categories[action.categoryId],
            notes: [...state.categories[action.categoryId].notes, action.note],
          },
        },
      };
    case NOTE_CATEGORY_CREATE:
      return {
        ...state,
        categories: {
          ...state.categories,
          [action.categoryId]: {
            name: action.name,
            notes: [],
          },
        },
      };
    case NOTE_UPDATE:
      return {
        ...state,
      };
    case NOTE_DELETE:
      let newNotes = state.categories[action.categoryId].notes.filter((note) => {
        return note.id !== action.noteId;
      });

      return {
        ...state,
        categories: {
          ...state.categories,
          [action.categoryId]: {
            ...state.categories[action.categoryId],
            notes: newNotes,
          },
        },
        currentNote: null,
      };

    case NOTE_SET:
      return {
        ...state,
        currentNote: action.note,
        currentCategory: action.categoryId,
      };
    case NOTES_DATA_FETCH:
      return {
        ...state,
        categories: action.data,
      };
    default:
      return state;
  }
};
