import React, { useCallback, useEffect, useState } from 'react';
import { useSelector, useDispatch } from 'react-redux';

import {
  deleteNote,
  deleteAssociatedPhotos,
  fetchNotes,
  updateNote,
  logoutUser,
  createNoteCategory,
} from '../actions';

import { Button, Grid, Header, Message, Divider, Input, Segment } from 'semantic-ui-react';

import Note from '../components/Note';
import NotePhoto from '../components/NotePhoto';
import CategoryList from '../components/CategoryList';

const Home = () => {
  const auth = useSelector((state) => state.auth);
  const notes = useSelector((state) => state.notes);
  const photos = useSelector((state) => state.photos);
  const dispatch = useDispatch();

  const [newCategoryName, setNewCategoryName] = useState('');

  const addCategory = () => {
    dispatch(createNoteCategory(auth.user.uid, newCategoryName));
    setNewCategoryName('');
  };

  const loadNotes = useCallback(() => {
    dispatch(fetchNotes(auth.user.uid));
  }, [auth.user.uid, dispatch]);

  const handleChange = (e) => {
    setNewCategoryName(e.target.value);
  };

  const handleDelete = () => {
    dispatch(deleteNote());
    dispatch(deleteAssociatedPhotos(photos.urls));
  };

  const handleLogout = () => {
    dispatch(logoutUser());
  };

  const handleSave = () => {
    dispatch(updateNote());
  };

  useEffect(() => {
    loadNotes();
  }, [loadNotes]);

  return (
    <Grid className="ml-3">
      <Grid.Row>
        <Grid.Column textAlign="center" verticalAlign="middle">
          <Header className="mt-4">Notey McNoteface</Header>
        </Grid.Column>
      </Grid.Row>
      <Grid.Row divided>
        <Grid.Column width={4}>
          <Header className="ml-3">Categories</Header>
          <CategoryList categories={notes.categories} />
          <Segment>
            <Input
              className="ml-4"
              name="title"
              value={newCategoryName}
              placeholder="Category Name"
              onChange={(e) => handleChange(e)}
            />
            <Button className="ml-4" onClick={addCategory}>
              Add Category
            </Button>
          </Segment>
        </Grid.Column>
        <Grid.Column width={12}>
          <Header>Current Note</Header>
          <Note currentCategory={notes.currentCategory} note={notes.currentNote} />
          <NotePhoto note={notes.currentNote} />
        </Grid.Column>
      </Grid.Row>
      <Grid.Row>
        <Grid.Column textAlign="center">
          <Button content="Save Note" onClick={handleSave} positive />
          <Button content="Delete Note" negative onClick={handleDelete} />
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
