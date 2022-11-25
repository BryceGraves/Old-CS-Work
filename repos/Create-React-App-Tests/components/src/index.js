import React from 'react';
import ReactDOM from 'react-dom';
import faker from 'faker';

import CommentDetail from './CommentDetail';
import ApprovalCard from './ApprovalCard';

const App = () => (
  <div className="ui container comments">
    <ApprovalCard>Are you sure you want to do this?</ApprovalCard>
    <ApprovalCard>
      <CommentDetail 
        avatar={faker.image.avatar()} 
        author="Sam"
        timePosted="Yesterday at 5:00PM"
        comment={faker.lorem.sentence()} 
      />
    </ApprovalCard>
    <ApprovalCard>
      <CommentDetail 
        avatar={faker.image.avatar()} 
        author="Alex"
        timePosted="Today at 2:00AM"
        comment={faker.lorem.sentence()} 
      />
    </ApprovalCard>
    <ApprovalCard>
      <CommentDetail 
        avatar={faker.image.avatar()} 
        author="Jane"
        timePosted="Today at 4:45PM"
        comment={faker.lorem.sentence()} 
      />
    </ApprovalCard>
  </div>
);

ReactDOM.render(<App /> , document.querySelector("#root"));
