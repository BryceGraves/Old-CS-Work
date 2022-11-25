import React from "react";

import { Link } from "react-router-dom";

import {
  Button,
  Form,
  Grid,
  Header,
  Icon,
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
    completed: true,
    icon: 'payment',
    title: 'Pay',
  },
  {
    key: 'confirmation',
    active: true,
    icon: 'info',
    title: 'Confirmation'
  },
]

const ConfirmationSteps = () => <Step.Group items={steps} />

function Confirmation({ globalState }) {
  const {
    firstName,
    lastName,
    schoolName,
    districtName,
    billingAddress,
    zipCode,
    city,
    stateCode
  } = globalState.formInfo;

  return (
    <Segment placeholder>
      <ConfirmationSteps />
      <Grid>
        <Grid.Row>
          <Grid.Column width={8}>
            <Header as='h3' style={{ fontSize: '2em', marginTop: '2rem' }}>
                Your order has been placed:
            </Header>
            <p style={{ fontSize: '1.3em' }}>
              Thank you for purchasing our product! A custom url has been generated for you.
            </p>
            <p style={{ fontSize: '1.3em' }}>
              The button below will redirect you to your school's scheduling software where you will be prompted to log in and complete the setup.
            </p>
            <a href="https://falcontime.herokuapp.com/users/sign_in">
              <Button size='huge'>
                Setup
                <Icon name="arrow alternate circle right outline" />
              </Button>
            </a>
          </Grid.Column>
          <Grid.Column width={8}>
            <Header as='h3' style={{ fontSize: '2em', marginTop: '2rem' }}>
                Order Information:
            </Header>
            <Form>
              <Form.Group widths={2} inline>
                <Form.Input
                  fluid
                  readOnly
                  name='firstName'
                  value={firstName || ""}
                  label='First name' />
                <Form.Input
                  fluid
                  readOnly
                  name='lastName'
                  value={lastName || ""}
                  label='Last name' />
                <Form.Input
                  fluid
                  readOnly
                  name='schoolName'
                  value={schoolName || ""}
                  label='School Name' />
                <Form.Input
                  fluid
                  readOnly
                  name='districtName'
                  value={districtName || ""}
                  label='District Name' />
              </Form.Group>
              <Form.Group widths={4} inline>
                <Form.Input
                  fluid
                  readOnly
                  name='billingAddress'
                  value={billingAddress || ""}
                  label='Billing Address' />
                <Form.Input
                  fluid
                  readOnly
                  name='zipCode'
                  value={zipCode || ""}
                  label='Zip Code' />
                <Form.Input
                  fluid
                  readOnly
                  name='city'
                  value={city || ""}
                  label='City' />
                <Form.Input
                  fluid
                  readOnly
                  name='stateCode'
                  value={stateCode || ""}
                  label='State' />
              </Form.Group>
            </Form>
          </Grid.Column>
        </Grid.Row>
      </Grid>
    </Segment>
  )
}

export default Confirmation
