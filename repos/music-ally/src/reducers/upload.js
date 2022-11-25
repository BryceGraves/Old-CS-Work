import { UPLOAD_FINISH, UPLOAD_START, UPLOAD_PROGRESS } from '../actions';

export default (
  state = {
    uploading: false,
    progress: 0,
  },
  action
) => {
  switch (action.type) {
    case UPLOAD_START:
      return {
        ...state,
        uploading: true,
      };
    case UPLOAD_FINISH:
      return {
        ...state,
        progress: 0,
        uploading: false,
      };
    case UPLOAD_PROGRESS:
      return {
        ...state,
        progress: state.progress + action.progress,
      };
    default:
      return state;
  }
};
