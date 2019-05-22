import React, { Component } from "react";
import {Form, Button, Col} from 'react-bootstrap';

import "popper.js/dist/popper.min.js";
import "bootstrap/dist/css/bootstrap.min.css";

import "./Login.css";

export default class Login extends Component {
    constructor(props) {
        super(props);

        this.state = {
            email: "",
            password: ""
        };
    }

    validateForm() {
        return this.state.email.length > 0 && this.state.password.length > 0;
    }
    
    handleChange = event => {
        this.setState({
            [event.target.id]: event.target.value
        });
    }

    handleSubmit = event => {
        event.preventDefault();
    }

    render() {
        return (
            <React.Fragment>
              <Form onSubmit={this.handleSubmit}>
		<Form.Row>
                  <Form.Group as={Col} md={{span:4, offset:4}} controlId="email" bsSize="large">
                    <Form.Control
                      autoFocus
                      type="email"
                      placeholder="Email Address"
                      value={this.state.email}
                      onChange={this.handleChange} />
                    <Form.Text className="text-muted">
                      We'll never share your email with anyone else.
                    </Form.Text>
                  </Form.Group>
                </Form.Row>
                
                <Form.Row>                   
                  <Form.Group as={Col}  md={{span:4, offset:4}} controlId="password" bsSize="large">
                    <Form.Control
                      placeholder="Password"
                      value={this.state.password}
                      onChange={this.handleChange}
                      type="password"
                    />
                  </Form.Group>
                </Form.Row>
                
                <span className="d-flex flex-row justify-content-center">
                  <Button variant="secondary" disabled={!this.validateForm()} type="submit" >
                    Login
                  </Button>
                </span>
              </Form>
            </React.Fragment>
        );
    }
}
