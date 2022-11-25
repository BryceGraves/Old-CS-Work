import axios from 'axios';

export const USER_DATA_SONG_ADD = 'USER_DATA_SONGS_ADD';
export const USER_DATA_SONG_SET = 'USER_DATA_SONG_SET';
export const USER_DATA_SONG_UPDATE = 'USER_DATA_SONG_UPDATE';

export const USER_DATA_FETCH = 'USER_DATA_FETCH';

const songAdd = (songData) => {
  return {
    type: USER_DATA_SONG_ADD,
    songData: songData,
  };
};

const songSet = (song) => {
  return {
    type: USER_DATA_SONG_SET,
    song: song,
  };
};

const songUpdate = (newSongPath, oldSongPath, newItemIndex) => {
  return {
    type: USER_DATA_SONG_UPDATE,
    newSongPath,
    oldSongPath,
    newItemIndex,
  };
};

const dataFetch = (data) => {
  return {
    type: USER_DATA_FETCH,
    data: data,
  };
};

export const queueSong = (song) => {
  const [artist, album, title] = song.key.split('/');
  const queueUrl = 'http://ec2-18-232-76-92.compute-1.amazonaws.com:8080/play';

  return axios
    .post(queueUrl, {
      Artist: artist,
      Album: album,
      Song: title,
    })
    .then((response) => {
      console.log(`Server Response: `, response);
    })
    .catch((error) => {
      console.log('Error:', error);
    });
};

export const addSong = (genre, artist, album, name) => (dispatch) => {
  const newSong = {
    [genre]: {
      [artist]: {
        [album]: [
          {
            name: name,
            key: genre + '/' + artist + '/' + album + '/' + name,
          },
        ],
      },
    },
  };

  const addUrl = 'http://ec2-18-232-76-92.compute-1.amazonaws.com:8080/addSong';

  return axios
    .post(addUrl, {
      Genre: genre,
      Artist: artist,
      Album: album,
      Song: name,
    })
    .then((response) => {
      console.log(`Server Response: `, response);
      dispatch(songAdd(newSong));
    })
    .catch((error) => {
      console.log('Error:', error);
    });
};

export const setSong = (song) => (dispatch) => {
  const fetchUrl = 'http://ec2-18-232-76-92.compute-1.amazonaws.com:8080/song?song=' + song.name;
  let songObject = song;

  return axios
    .get(fetchUrl)
    .then((response) => {
      songObject.url = response.data;
      dispatch(songSet(songObject));
      dispatch(queueSong(song));
    })
    .catch((error) => {
      console.log('Error:', error);
    });
};

export const fetchSongs = () => (dispatch) => {
  const fetchUrl = 'http://ec2-18-232-76-92.compute-1.amazonaws.com:8080/fetchSongs';

  return axios
    .get(fetchUrl)
    .then((response) => {
      console.log(response);
      dispatch(dataFetch(response.data));
    })
    .catch((error) => {
      console.log('Error:', error);
    });
};

export const updateSong = (newPath, oldPath) => (dispatch) => {
  const updateUrl = 'http://ec2-18-232-76-92.compute-1.amazonaws.com:8080/updateSong';

  return axios
    .post(updateUrl, {
      newPath,
      oldPath,
    })
    .then((response) => {
      console.log(`Server Response: `, response);

      // TODO: swap this to update and figure out how to map these
      dispatch(fetchSongs());
    })
    .catch((error) => {
      console.log('Error:', error);
    });
};
