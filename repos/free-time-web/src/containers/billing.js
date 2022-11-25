import React, { useCallback } from "react";

import { Link } from "react-router-dom";

import {
  Form,
  Grid,
  Header,
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
    active: true,
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

const BillingSteps = () => <Step.Group items={steps} />

function Billing({ updateGlobalState, globalState }) {
  const handleChange = useCallback((e, { name, value }) => {
    globalState.formInfo[name] = value
    updateGlobalState(globalState);
  }, []);

  const handleSubmit = useCallback(() => {
    updateGlobalState(globalState);
  }, []);

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
      <BillingSteps />
      <Grid>
        <Grid.Row>
          <Grid.Column width={8}>
            <Form>
              <Form.Group widths={4} inline>
                <Form.Input
                  fluid
                  name='firstName'
                  value={firstName}
                  label='First name'
                  placeholder='First name'
                  onChange={handleChange} />
                <Form.Input
                  fluid
                  name='lastName'
                  value={lastName}
                  label='Last name'
                  placeholder='Last name'
                  onChange={handleChange} />
                <Form.Input
                  fluid
                  name='schoolName'
                  value={schoolName}
                  label='School Name'
                  placeholder='School Name'
                  onChange={handleChange} />
                <Form.Input
                  fluid
                  name='districtName'
                  value={districtName}
                  label='District Name'
                  placeholder='District Name'
                  onChange={handleChange} />
              </Form.Group>
              <Form.Group widths={4} inline>
                <Form.Input
                  fluid
                  name='billingAddress'
                  value={billingAddress}
                  label='Billing Address'
                  placeholder='Billing Address'
                  onChange={handleChange} />
                <Form.Input
                  fluid
                  name='zipCode'
                  value={zipCode}
                  label='Zip Code'
                  placeholder='Zip Code'
                  onChange={handleChange} />
                <Form.Input
                  fluid
                  name='city'
                  value={city}
                  label='City'
                  placeholder='City'
                  onChange={handleChange} />
                <Form.Input
                  fluid
                  name='stateCode'
                  value={stateCode}
                  label='State'
                  placeholder='State'
                  onChange={handleChange} />
              </Form.Group>
              <Link to="/payment">
                <Form.Button onClick={handleSubmit}>Proceed to Payment</Form.Button>
              </Link>
            </Form>
          </Grid.Column>
          <Grid.Column width={8}>
            <Header as='h3' style={{ fontSize: '2em', marginTop: '2rem' }}>
                Billing Information
            </Header>
            <p style={{ fontSize: '1.33em' }}>
              We need a some information about you to complete your order.
            </p>
          </Grid.Column>
        </Grid.Row>
      </Grid>
    </Segment>
  )
}

export default Billing
