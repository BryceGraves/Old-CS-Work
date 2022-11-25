import React, { useCallback, useEffect, useState } from 'react';
import { useDispatch, useSelector } from 'react-redux';

import { fetchNotePhotos, uploadNotePhotos } from '../actions';

import { Divider, Header, Input, Image, ImageGroup, Progress, Segment } from 'semantic-ui-react';

/**
 * TODO: describe what params this component needs and what it does
 */
const NotePhoto = ({ note }) => {
  const dispatch = useDispatch();

  const photos = useSelector((state) => state.photos);
  const [selectedFiles, setSelectedFiles] = useState(null);

  const fetchPhotos = useCallback(() => {
    dispatch(fetchNotePhotos());
  }, [dispatch]);

  const handleFilesSelected = (event) => {
    setSelectedFiles(event.target.files);
  };

  const handleUpload = () => {
    const filesAsArray = Array.from(selectedFiles);
    dispatch(uploadNotePhotos(filesAsArray));
  };

  useEffect(() => {
    console.log('Note Photo Rendered');
    if (note) {
      console.log('Fetching Note Photos');
      fetchPhotos();
    }
  }, [fetchPhotos, note, photos.uploading]);

  if (!note) {
    return null;
  }

  if (photos && photos.uploading) {
    return (
      <Segment>
        <Header>Upload in Progress</Header>
        <Progress className="mb-2" percent={photos.progress} indicating />
      </Segment>
    );
  }

  if (photos && photos.urls.length === 0) {
    return (
      <>
        <Divider horizontal>ATTACH A PHOTO</Divider>
        <Input
          action={{
            content: 'Upload Files',
            icon: 'upload',
            onClick: handleUpload,
          }}
          multiple
          onChange={handleFilesSelected}
          type="file"
        />
      </>
    );
  }

  const images = photos.urls.map((url) => {
    return <Image src={url} />;
  });

  return (
    <>
      <Divider horizontal>PHOTOS</Divider>
      <ImageGroup size="large">{images}</ImageGroup>
      <Divider horizontal>ADD MORE PHOTOS</Divider>
      <Input
        action={{
          content: 'Upload Files',
          icon: 'upload',
          onClick: handleUpload,
        }}
        multiple
        onChange={handleFilesSelected}
        type="file"
      />
    </>
  );
};

export default NotePhoto;
