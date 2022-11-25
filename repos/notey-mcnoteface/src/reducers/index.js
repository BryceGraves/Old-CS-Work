import { combineReducers } from 'redux';
import auth from './auth';
import notes from './notes';
import photos from './photos';

export default combineReducers({ auth, notes, photos });
