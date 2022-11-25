import {
  USER_DATA_SONG_ADD,
  USER_DATA_SONG_SET,
  USER_DATA_SONG_UPDATE,
  USER_DATA_FETCH,
} from '../actions';

export default (
  state = {
    music: {},
    currentSong: {},
  },
  action
) => {
  switch (action.type) {
    case USER_DATA_SONG_ADD:
      return {
        ...state,
        music: { ...state.music, ...action.songData },
      };
    case USER_DATA_SONG_SET:
      return {
        ...state,
        currentSong: action.song,
      };
    case USER_DATA_SONG_UPDATE:
      // TODO: figure out how to actually map this well

      return {
        ...state,
        music: state.music,
      };
    case USER_DATA_FETCH:
      return {
        ...state,
        music: action.data,
      };
    default:
      return state;
  }
};
