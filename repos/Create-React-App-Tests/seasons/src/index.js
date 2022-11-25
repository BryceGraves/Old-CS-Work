// Import the React and ReactDOM libraries
import React from 'react';
import ReactDOM from 'react-dom';

import SeasonDisplay from './SeasonDisplay';
import Loading from './Loader';

// Create a react component
class App extends React.Component {
  state = { lat: null, errorMessage: ''};

  componentDidMount() {
    window.navigator.geolocation.getCurrentPosition(
      position => this.setState({ lat: position.coords.latitude}),
      err => this.setState({ errorMessage: err.message})
    );
  }

  componentDidUpdate() {
    console.log('My compontent re-rendered')
  }

  renderContent() {
    if (this.state.errorMessage && !this.state.lat) {
      return <div>Error: {this.state.errorMessage}</div>;
    }
    
    if (!this.state.errorMessage && this.state.lat) {
      return <SeasonDisplay lat={this.state.lat} />;
    }
    
    return <div><Loading message="Please accept location request"/></div>;
  }

  render() {
    return (
      <div>
        {this.renderContent()}
      </div>
    );
  };
}

// Take the react component and show it on the screen
ReactDOM.render(<App />, document.querySelector("#root"));
