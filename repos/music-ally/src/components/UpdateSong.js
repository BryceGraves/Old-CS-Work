import React, { useEffect, useState } from 'react';
import { useDispatch } from 'react-redux';

import { updateSong } from '../actions';

import { Button, Divider, Form, Header, Segment } from 'semantic-ui-react';

/**
 * TODO: describe what params this component needs and what it does
 */
const UpdateSong = ({ song }) => {
  const [songGenreState, setSongGenreState] = useState('');
  const [songArtistState, setSongArtistState] = useState('');
  const [songAlbumState, setSongAlbumState] = useState('');
  const [songNameState, setSongNameState] = useState('');

  const dispatch = useDispatch();

  useEffect(() => {
    if (song.key) {
      const splitSong = song.key.split('/');

      setSongGenreState(splitSong[0]);
      setSongArtistState(splitSong[1]);
      setSongAlbumState(splitSong[2]);
      setSongNameState(splitSong[3]);
    }
  }, [song.key]);

  const handleSave = () => {
    dispatch(
      updateSong(
        songGenreState + '/' + songArtistState + '/' + songAlbumState + '/' + songNameState,
        song.key
      )
    );
  };

  if (!song.key) {
    return null;
  }

  return (
    <>
      <Segment>
        <Form>
          <Header>Update Song</Header>
          <Divider />
          <Form.Group>
            <Form.Input
              name="genre"
              value={songGenreState}
              onChange={(e) => setSongGenreState(e.target.value)}
              placeholder="Genre"
            />
            <Form.Input
              name="artist"
              value={songArtistState}
              onChange={(e) => setSongArtistState(e.target.value)}
              placeholder="Artist"
            />
            <Form.Input
              name="album"
              value={songAlbumState}
              onChange={(e) => setSongAlbumState(e.target.value)}
              placeholder="Album"
            />
            <Form.Input
              name="title"
              value={songNameState}
              onChange={(e) => setSongNameState(e.target.value)}
              placeholder="Title"
            />
            <Button content="Save Song" onClick={handleSave} />
          </Form.Group>
        </Form>
      </Segment>
    </>
  );
};

export default UpdateSong;
