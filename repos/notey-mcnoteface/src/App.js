import React from 'react';

import { Route, Switch } from 'react-router-dom';
import { connect } from 'react-redux';

import ProtectedRoute from './routes/ProtectedRoute';
import Home from './containers/Home';
import Login from './containers/Login';

const mapStateToProps = (state) => {
  return {
    isAuthenticated: state.auth.isAuthenticated,
    isVerifying: state.auth.isVerifying,
  };
};

const App = (props) => {
  const { isAuthenticated, isVerifying } = props;
  return (
    <Switch>
      <ProtectedRoute
        exact
        path="/"
        component={Home}
        isAuthenticated={isAuthenticated}
        isVerifying={isVerifying}
      />
      <Route path="/login" component={Login} />
    </Switch>
  );
};

export default connect(mapStateToProps)(App);
