import React, { useCallback, useState } from "react";

import { Link } from "react-router-dom";

import {
  Button,
  Card,
  Segment,
  Step,
} from 'semantic-ui-react'

const steps = [
  {
    key: 'shopping',
    active: true,
    icon: 'shopping cart',
    title: 'Shopping',
  },
  {
    key: 'billing',
    disabled: true,
    icon: 'address card outline',
    title: 'Billing',
  },
  {
    key: 'payment',
    disabled: true,
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

const CheckoutSteps = () => <Step.Group items={steps} />

function Storefront({updateGlobalState, globalState}) {
  const handleSubmit = useCallback((cost) => {
    globalState.paymentPlan.amount = cost

    if (cost === 5000) {
      globalState.paymentPlan.description = "Trial Subscription"
    } else if (cost === 100000) {
      globalState.paymentPlan.description = "Year Subscription"
    }

    updateGlobalState(globalState);
  }, []);

  return (
    <>
      <Segment placeholder>
        <CheckoutSteps />
        <Card.Group centered>
          <Card>
            <Card.Content>
              <Card.Header textAlign="center">Trial</Card.Header>
              <Card.Meta>Non-Recurring</Card.Meta>
              <Card.Description>
                Month long trial of the scheduling software
              </Card.Description>
            </Card.Content>
            <Card.Content extra>
              <Link to="/billing">
                <Button basic color='green' onClick={() => handleSubmit(5000)}>Price: $50</Button>
              </Link>
            </Card.Content>
          </Card>
          <Card>
            <Card.Content>
              <Card.Header textAlign="center">Yearly Subscription</Card.Header>
              <Card.Meta>Recurring Annually</Card.Meta>
              <Card.Description>
                Year long subscription
              </Card.Description>
            </Card.Content>
            <Card.Content extra>
              <Link to="/billing">
                <Button basic color='green' onClick={() => handleSubmit(100000)}>Price: $1000</Button>
              </Link>
            </Card.Content>
          </Card>
        </Card.Group>
      </Segment>
    </>
  );
}

export default Storefront
