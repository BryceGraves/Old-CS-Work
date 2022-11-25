import React, { useState } from 'react';
import { useDispatch } from 'react-redux';

import { addSong } from '../actions';

import { Button, Divider, Form, Header, Segment } from 'semantic-ui-react';

/**
 * TODO: describe what params this component needs and what it does
 */
const AddSong = () => {
  const [songGenreState, setSongGenreState] = useState('');
  const [songArtistState, setSongArtistState] = useState('');
  const [songAlbumState, setSongAlbumState] = useState('');
  const [songNameState, setSongNameState] = useState('');

  const dispatch = useDispatch();

  const handleSave = () => {
    dispatch(addSong(songGenreState, songArtistState, songAlbumState, songNameState));
  };

  return (
    <>
      <Segment>
        <Form>
          <Header>Add Song</Header>
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

export default AddSong;
