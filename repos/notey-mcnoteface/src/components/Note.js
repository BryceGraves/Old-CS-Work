import React from 'react';
import { useDispatch } from 'react-redux';

import { setNote } from '../actions';

import { Form, Header, Message } from 'semantic-ui-react';

/**
 * TODO: describe what params this component needs and what it does
 */
const Note = ({ currentCategory, note }) => {
  const dispatch = useDispatch();

  const handleChange = (_, { name, value }) => {
    let newNote = note;
    newNote[name] = value;

    dispatch(setNote(currentCategory, newNote));
  };

  if (!note) {
    return (
      <>
        <Header>No Note Selected</Header>
        <Message>Please select a note</Message>
      </>
    );
  }

  return (
    <>
      <Form>
        <Form.Input name="title" value={note.title} onChange={handleChange} placeholder="Title" />
        <Form.TextArea
          name="content"
          value={note.content}
          onChange={handleChange}
          placeholder="Content"
        />
      </Form>
    </>
  );
};

export default Note;
