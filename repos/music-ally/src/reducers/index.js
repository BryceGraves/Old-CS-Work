import { combineReducers } from 'redux';
import auth from './auth';
import userData from './userData';
import upload from './upload';

export default combineReducers({ auth, userData, upload });
