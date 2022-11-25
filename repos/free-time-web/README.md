# Web-based Startup Functional Prototype

Source repo for senior web based startup project

## Prerequisites

1. An adequate version of [`Node.js`](https://nodejs.org/) is installed.

    ```sh
    $ node --version
    v6.10.1
    ```

2. An adequate version of  [`npm`](https://nodejs.org/) is installed.

    ```sh
    $ npm --version
    3.10.10
    ```

## Setup

Important note: these setup instructions support linux and WSL (with host forwarding configured for local hosting)

### Local Environment

Run [yarn install](#yarn-install) to ensure node modules are installed on your local machine

### Running Application

This shouldn't be an issue. The application `should` run on `http://localhost:3000/` and open automagically when [yarn start](#yarn-start) is run

Changes to application code are loaded on webpage after every save. Since this app is a SPA the hot reload resets the page back to landing for now.

## Important Scripts

List of important scripts available through `yarn` package manager:

### `yarn install`

Installs required packages in `node_modules`

Note: these are not kept in the repo and must be installed locally

### `yarn start`

Runs the app in the development mode.

Open [http://localhost:3000](http://localhost:3000) to view it in the browser.

The page will reload if you make edits.

You will also see any lint errors in the console.

### `yarn deploy`

Builds the app for production to the `build` folder.

It correctly bundles React in production mode and optimizes the build for the best performance.

The build is minified and the filenames include the hashes.

This then deploys the newly built app to gh-pages.
