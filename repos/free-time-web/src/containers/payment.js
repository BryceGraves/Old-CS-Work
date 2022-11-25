import React from "react";

import { Elements, StripeProvider } from 'react-stripe-elements';

import CheckoutForm from '../components/checkoutForm';


import {
  Segment,
  Step,
} from 'semantic-ui-react'

const steps = [
  {
    key: 'shopping',
    completed: true,
    icon: 'shopping cart',
    title: 'Shopping',
  },
  {
    key: 'billing',
    completed: true,
    icon: 'address card outline',
    title: 'Billing',
  },
  {
    key: 'payment',
    active: true,
    icon: 'payment',
    title: 'Pay',
  },
  {
    key: 'confirmation',
    disabled: true,
    icon: 'info',
    title: 'Confirmation'
  },
]

const PaymentSteps = () => <Step.Group items={steps} />

function Payment({globalState}) {
  return (
    <Segment placeholder>
      <PaymentSteps />
      <StripeProvider apiKey="pk_test_ae2dqlbeTWbXTJQiTPq80y5I00jRIfAKcM">
        <div className="example">
          <h1>Input Your Payment Information Below</h1>
          <Elements>
            <CheckoutForm amount={globalState.paymentPlan.amount} description={globalState.paymentPlan.description} />
          </Elements>
        </div>
      </StripeProvider>
    </Segment>
  );
}

export default Payment
