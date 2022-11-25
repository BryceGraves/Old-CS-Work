import * as AWS from 'aws-sdk';

export const UPLOAD_START = 'UPLOAD_START';
export const UPLOAD_FINISH = 'UPLOAD_FINISH';
export const UPLOAD_PROGRESS = 'UPLOAD_PROGRESS';

const uploadStart = () => {
  return {
    type: UPLOAD_START,
  };
};

const uploadFinish = () => {
  return {
    type: UPLOAD_FINISH,
  };
};

const uploadProgress = (progress) => {
  return {
    type: UPLOAD_PROGRESS,
    progress: progress,
  };
};

export const upload = (metaData, file) => (dispatch, getState) => {
  const state = getState();
  const postUrl = 'http://localhost:8080/upload';

  const reader = new FileReader();

  reader.onabort = () => {
    console.log('file reading was aborted');
  };
  reader.onerror = () => {
    console.log('file reading has failed');
  };
  reader.onloadend = () => {
    const xhr = new XMLHttpRequest();
    xhr.open('POST', postUrl, true);
    xhr.send(reader.result);
  };

  reader.readAsArrayBuffer(file);
};
