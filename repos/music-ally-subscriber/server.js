const express = require('express');
const cors = require('cors');
const port = 8081;

const AWS = require('aws-sdk');
AWS.config.region = 'us-east-1';
const sqs = new AWS.SQS();

const app = express();
app.use(express.json());
app.use(cors());

app.get('/', (req, res) => {
  res.send("OWO what's this? An SQS server?!");
});

const receiveMessageParams = {
  QueueUrl: 'https://sqs.us-east-1.amazonaws.com/576322095525/MusicAlly',
  VisibilityTimeout: 20,
};

setInterval(() => {
  sqs.receiveMessage(receiveMessageParams, (err, data) => {
    if (err) {
      console.log('Error receiving message from queue: ', err);
    } else {
      if (data.Messages) {
        const deleteMessageParams = {
          QueueUrl: 'https://sqs.us-east-1.amazonaws.com/576322095525/MusicAlly',
          ReceiptHandle: data.Messages[0].ReceiptHandle,
        };

        console.log('Received Message: ', data.Messages[0]);
        sqs.deleteMessage(deleteMessageParams, (err, data) => {
          if (err) {
            console.log('Error deleting message from queue: ', err);
          }
        });
      } else {
        console.log('Queue empty!');
      }
    }
  });
}, 5000);

app.listen(port, () => console.log(`Server be listening on port ${port}!`));
