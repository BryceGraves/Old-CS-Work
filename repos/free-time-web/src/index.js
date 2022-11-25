import React, { useCallback, useState } from "react";
import ReactDOM from "react-dom";
import {
  Route,
  HashRouter
} from "react-router-dom";

import Billing from "./containers/billing";
import Checkout from "./containers/checkout";
import LandingPage from "./containers/landingPage";
import Payment from "./containers/payment";
import Storefront from "./containers/storefront";

import 'semantic-ui-css/semantic.min.css'

function App() {
  const [globalState, setGlobalState] = useState({
    formInfo: {
      firstName: "",
      lastName: "",
      schoolName: "",
      districtName: "",
      creditCardNumber: "",
      securityCode: "",
      billingAddress: "",
      zipCode: "",
      city: "",
      stateCode: ""
    },
    paymentPlan: {
      amount: 100000,
      description: ""
    }
  });

  const handleGlobalStateUpdate = useCallback((updatedValues) => {
      setGlobalState((prevValues) => {
        return { ...prevValues, ...updatedValues }
      });
  }, []);

  return (
    <HashRouter>
      <Route path="/store" exact>
        <Storefront
          updateGlobalState={handleGlobalStateUpdate}
          globalState={globalState} />
      </Route>
      <Route path="/billing" exact>
        <Billing
          updateGlobalState={handleGlobalStateUpdate}
          globalState={globalState} />
      </Route>
      <Route path="/payment" exact>
        <Payment globalState={globalState} />
      </Route>
      <Route path="/confirmation" exact>
        <Checkout globalState={globalState} />
      </Route>
      <Route path="/" exact>
        <LandingPage />
      </Route>
    </HashRouter>
  );
}

ReactDOM.render(
  <App />,
  document.querySelector("#root")
);