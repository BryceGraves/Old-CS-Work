import axios from 'axios';

import { myFirebase } from '../firebase/';
import firebase from 'firebase/app';

export const LOGIN_REQUEST = 'LOGIN_REQUEST';
export const LOGIN_SUCCESS = 'LOGIN_SUCCESS';
export const LOGIN_FAILURE = 'LOGIN_FAILURE';

export const LOGOUT_REQUEST = 'LOGOUT_REQUEST';
export const LOGOUT_SUCCESS = 'LOGOUT_SUCCESS';
export const LOGOUT_FAILURE = 'LOGOUT_FAILURE';

export const VERIFY_REQUEST = 'VERIFY_REQUEST';
export const VERIFY_SUCCESS = 'VERIFY_SUCCESS';

export const SIGNUP_REQUEST = 'SIGNUP_REQUEST';
export const SIGNUP_FAILURE = 'SIGNUP_FAILURE';

const requestLogin = () => {
  return {
    type: LOGIN_REQUEST,
  };
};

const receiveLogin = (user) => {
  return {
    type: LOGIN_SUCCESS,
    user,
  };
};

const loginError = () => {
  return {
    type: LOGIN_FAILURE,
  };
};

const requestLogout = () => {
  return {
    type: LOGOUT_REQUEST,
  };
};

const receiveLogout = () => {
  return {
    type: LOGOUT_SUCCESS,
  };
};

const logoutError = () => {
  return {
    type: LOGOUT_FAILURE,
  };
};

const verifyRequest = () => {
  return {
    type: VERIFY_REQUEST,
  };
};

const verifySuccess = () => {
  return {
    type: VERIFY_SUCCESS,
  };
};

const signupRequest = () => {
  return {
    type: SIGNUP_REQUEST,
  };
};

const signupFailure = () => {
  return {
    type: SIGNUP_FAILURE,
  };
};

export const loginUserEmail = (email, password) => (dispatch) => {
  dispatch(requestLogin());

  myFirebase
    .auth()
    .signInWithEmailAndPassword(email, password)
    .then((result) => {
      dispatch(receiveLogin(result.user));
    })
    .catch((error) => {
      // TODO: this
      console.log('Email Login Error: ' + error);
      dispatch(loginError());
    });
};

export const loginUserGoogle = () => (dispatch) => {
  dispatch(requestLogin());

  var provider = new firebase.auth.GoogleAuthProvider();

  myFirebase
    .auth()
    .signInWithPopup(provider)
    .then((result) => {
      dispatch(receiveLogin(result.user));
    })
    .catch((error) => {
      // TODO: this
      console.log('Google Login Error: ' + error);
      dispatch(loginError());
    });
};

export const signUpEmail = (email, password) => (dispatch) => {
  dispatch(signupRequest());

  myFirebase
    .auth()
    .createUserWithEmailAndPassword(email, password)
    .catch((error) => {
      // TODO: this
      console.log('SignUp with Email Error: ' + error.code);
      dispatch(signupFailure());
    });
};

export const logoutUser = () => (dispatch) => {
  dispatch(requestLogout());

  myFirebase
    .auth()
    .signOut()
    .then(() => {
      dispatch(receiveLogout());
    })
    .catch((error) => {
      // TODO: this
      console.log('Logout user error: ' + error);
      dispatch(logoutError());
    });
};

export const verifyAuth = () => (dispatch) => {
  dispatch(verifyRequest());

  myFirebase.auth().onAuthStateChanged((user) => {
    if (user !== null) {
      dispatch(receiveLogin(user));
    }

    dispatch(verifySuccess());
  });
};
