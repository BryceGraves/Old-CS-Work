import React from 'react';
import { Route, Redirect } from 'react-router-dom';

// TODO: create route protection for multiple routes
const ProtectedRoute = ({ component: Component, isAuthenticated, isVerifying, ...rest }) => (
  <Route
    {...rest}
    render={(props) =>
      isVerifying ? (
        <div />
      ) : isAuthenticated ? (
        <Component {...props} />
      ) : (
        <Redirect
          to={{
            pathname: '/login',
            state: { from: props.location },
          }}
        />
      )
    }
  />
);

export default ProtectedRoute;
