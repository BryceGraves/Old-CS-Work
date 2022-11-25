import React, { useState } from 'react';
import { useDispatch, useSelector } from 'react-redux';
import { Redirect } from 'react-router-dom';

import { loginUserGoogle, loginUserEmail, signUpEmail } from '../actions';

import { Button, Divider, Form, Grid, Header, Message, Segment } from 'semantic-ui-react';

const Login = () => {
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');

  const loginError = useSelector((state) => state.auth.loginError);
  const isAuthenticated = useSelector((state) => state.auth.isAuthenticated);

  const dispatch = useDispatch();

  const handleSubmit = () => {
    dispatch(loginUserEmail(email, password));
  };

  const handleSignUp = () => {
    dispatch(signUpEmail(email, password));
  };

  const handleGoogleLogin = () => {
    dispatch(loginUserGoogle());
  };

  if (isAuthenticated) {
    return <Redirect to="/" />;
  }

  return (
    <Grid textAlign="center" style={{ height: '100vh' }} verticalAlign="middle">
      <Grid.Column style={{ maxWidth: 450 }}>
        <Form size="large">
          <Segment>
            <Header as="h1" color="black" textAlign="center">
              Login
            </Header>
            <Divider />
            <Form.Input
              fluid
              icon="user"
              iconPosition="left"
              placeholder="Email"
              onChange={(e) => setEmail(e.target.value)}
            />
            <Form.Input
              fluid
              icon="lock"
              iconPosition="left"
              placeholder="Password"
              type="password"
              onChange={(e) => setPassword(e.target.value)}
            />
            {loginError && (
              <Message negative>
                <Message.Header>Error Logging In</Message.Header>
                <p>Incorrect Email or Password</p>
              </Message>
            )}
            <Button color="black" fluid size="large" onClick={handleSubmit}>
              Sign In
            </Button>
            <Divider horizontal>OR</Divider>
            <Button color="black" fluid size="large" onClick={handleSignUp}>
              Sign Up
            </Button>
          </Segment>
        </Form>
        <Message>
          <Message.Header>Other Sign In Methods</Message.Header>
          <Divider />
          <Button color="google plus" fluid size="large" onClick={handleGoogleLogin}>
            Google
          </Button>
        </Message>
      </Grid.Column>
    </Grid>
  );
};

export default Login;
