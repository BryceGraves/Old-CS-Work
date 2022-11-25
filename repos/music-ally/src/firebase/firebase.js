import firebase from 'firebase/app';
import 'firebase/auth';
import 'firebase/firestore';
import 'firebase/storage';

const firebaseConfig = {
  apiKey: process.env.REACT_APP_API,
  authDomain: process.env.REACT_APP_DOMAIN,
  databaseURL: process.env.REACT_APP_DATABASE,
  projectId: process.env.REACT_APP_PROJECT,
  storageBucket: process.env.REACT_APP_STORAGE,
  messagingSenderId: process.env.REACT_APP_SENDER,
  appId: process.env.REACT_APP_APP,
};

export const myFirebase = firebase.initializeApp(firebaseConfig);

const baseDB = firebase.firestore();
const baseStorage = firebase.storage();
const baseRef = baseStorage.ref();

export const db = baseDB;
export const storage = baseStorage;
export const storageRef = baseRef;
