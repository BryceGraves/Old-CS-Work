import React, { useCallback, useEffect, useState } from 'react';
import { useSelector, useDispatch } from 'react-redux';

import { fetchSongs, logoutUser } from '../actions';

import { Button, Grid, Header, Message, Divider } from 'semantic-ui-react';

import Song from '../components/Song';
import AddSong from '../components/AddSong';
import UpdateSong from '../components/UpdateSong';
import GenreList from './GenreList';

const Home = () => {
  const auth = useSelector((state) => state.auth);
  const userData = useSelector((state) => state.userData);
  const dispatch = useDispatch();
  const debug = false;

  const loadSongs = useCallback(() => {
    dispatch(fetchSongs(auth.user.uid));
  }, [auth.user.uid, dispatch]);

  const handleLogout = () => {
    dispatch(logoutUser());
  };

  useEffect(() => {
    loadSongs();
  }, [loadSongs]);

  return (
    <Grid className="ml-3">
      <Grid.Row>
        <Grid.Column textAlign="center" verticalAlign="middle">
          <Header className="mt-4">Music Ally</Header>
          <Divider />
          {debug && <Message>{JSON.stringify(userData)}</Message>}
        </Grid.Column>
      </Grid.Row>
      <Grid.Row divided>
        <Grid.Column width={4}>
          <Header className="ml-3">Genres</Header>
          <Divider />
          <GenreList genres={userData.music} />
        </Grid.Column>
        <Grid.Column width={12}>
          <Header>Current Song</Header>
          <Song song={userData.currentSong} />
          <UpdateSong song={userData.currentSong} />
          <AddSong />
        </Grid.Column>
      </Grid.Row>
      <Grid.Row>
        <Grid.Column textAlign="center">
          <Divider />
          <Button onClick={handleLogout}>Logout</Button>
          {auth.isLoggingOut && <Message>Logging Out....</Message>}
          {auth.logoutError && <Message>Error logging out</Message>}
        </Grid.Column>
      </Grid.Row>
    </Grid>
  );
};

export default Home;
