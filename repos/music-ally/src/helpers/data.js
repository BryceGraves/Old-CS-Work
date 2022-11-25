import * as musicMetadata from 'music-metadata-browser';

import { addSongs, upload } from '../actions';

/**
 * TODO: add description of this
 */
export const extractAndUpload = (files) => (dispatch, getState) => {
  const state = getState();

  Promise.all(
    files.map((file) => {
      return musicMetadata
        .parseBlob(file)
        .then((metaData) => {
          const { album, artist, title } = metaData.common;
          return {
            album,
            artist,
            title,
          };
        })
        .catch((err) => {
          console.error(err.message);
        });
    })
  ).then((metaDataArray) => {
    let extractedData = {};

    metaDataArray.forEach((metaData, index) => {
      const {
        artist = metaData.artist || 'Unknown',
        album = metaData.album || 'Unknown',
        title = metaData.title || 'Unknown',
      } = metaData;

      const tempData = {};

      tempData[artist] = {};
      tempData[artist][album] = [
        {
          name: title,
          url: state.auth.user.uid + '/' + artist + '/' + album + '/' + title + '.mp3',
        },
      ];

      extractedData = { ...extractedData, ...tempData };

      dispatch(upload(metaData, files[index]));
      // filesToUpload = [...filesToUpload];
    });

    dispatch(addSongs(extractedData));
  });
};
