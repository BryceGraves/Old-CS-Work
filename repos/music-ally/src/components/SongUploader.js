import React, { useCallback } from 'react';
import { useDispatch } from 'react-redux';

import { useDropzone } from 'react-dropzone';
import { Message, Segment } from 'semantic-ui-react';

import { extractAndUpload } from '../helpers';

/**
 * TODO: describe what params this component needs and what it does
 */
const SongUploader = () => {
  const dispatch = useDispatch();

  const onDrop = useCallback(
    (acceptedFiles) => {
      dispatch(extractAndUpload(acceptedFiles));
    },
    [dispatch]
  );
  const { getRootProps, getInputProps, isDragActive } = useDropzone({ onDrop });

  return (
    <div {...getRootProps()}>
      <input {...getInputProps()} />
      <Segment color={isDragActive ? 'green' : null}>
        {isDragActive ? (
          <Message>Drop the files here ...</Message>
        ) : (
          <Message>Drag 'n' drop some files here, or click to select files</Message>
        )}
      </Segment>
    </div>
  );
};

export default SongUploader;
