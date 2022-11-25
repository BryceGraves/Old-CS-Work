import React from 'react';
import { useSelector, useDispatch } from 'react-redux';

import { createNote } from '../actions';

import { Segment, Header, Button } from 'semantic-ui-react';

import NoteList from './NoteList';

/**
 * TODO: describe what params this component needs and what it does
 */
const CategorySection = ({ category, categoryId }) => {
  const auth = useSelector((state) => state.auth);
  const dispatch = useDispatch();

  const addNote = () => {
    dispatch(createNote(auth.user.uid, categoryId, '', ''));
  };

  if (!category || !category.name) {
    return (
      <Segment>
        <Header>Category Name Loading</Header>
      </Segment>
    );
  }

  return (
    <Segment>
      <Header textAlign="center">{category.name}</Header>
      <NoteList categoryId={categoryId} notes={category.notes}></NoteList>
      <Button onClick={addNote}>Add Note</Button>
    </Segment>
  );
};

export default CategorySection;
