import React from 'react';
import { useDispatch } from 'react-redux';

import { setNote } from '../actions';

import { Button, Header, Message } from 'semantic-ui-react';

/**
 * TODO: describe what params this component needs and what it does
 */
const NoteList = ({ categoryId, notes }) => {
  const dispatch = useDispatch();

  if (notes.length === 0) {
    return (
      <>
        <Header>No Notes Created</Header>
        <Message>Please create a note</Message>
      </>
    );
  }

  const handleSetNote = (note) => {
    dispatch(setNote(categoryId, note));
  };

  const colorOptions = [
    'red',
    'orange',
    'yellow',
    'olive',
    'green',
    'teal',
    'blue',
    'violet',
    'purple',
    'pink',
    'brown',
    'grey',
    'black',
  ];

  const colorOptionsCount = colorOptions.length;

  const list = notes.map((note, index) => {
    return (
      <Button
        color={colorOptions[index % colorOptionsCount]}
        fluid
        onClick={(_) => handleSetNote(note)}
      >
        {note.title || 'Blank Title'}
      </Button>
    );
  });

  return (
    <Button.Group className="mb-3" fluid vertical>
      {list}
    </Button.Group>
  );
};

export default NoteList;
