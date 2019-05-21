import React, { Component } from "react";
import {Form, Button, Container, Row, Col} from 'react-bootstrap';

import "popper.js/dist/popper.min.js";
import "bootstrap/dist/css/bootstrap.min.css";

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
              <Container>
                <Form onSubmit={this.handleSubmit}>
                  <Row>
                    <Col md={{span:4, offset:4}} >
                      <Form.Group controlId="email" bsSize="large">
                        <Form.Control autoFocus type="email" value={this.state.email} onChange={this.handleChange} />
                      </Form.Group>
                    </Col>
                  </Row>
                  <Row>
                    <Col md={{span:4, offset:4}}>
                      <Form.Group controlId="password" bsSize="large">
                        <Form.Control
                          value={this.state.password}
                          onChange={this.handleChange}
                          type="password"
                        />
                      </Form.Group>
                    </Col>
                  </Row>
                  <Col md={{span:4, offset:4}}>
                    <span className="d-flex flex-row justify-content-center">
                      <Button variant="secondary" disabled={!this.validateForm()} type="submit" >
                        Login
                      </Button>
                    </span>
                  </Col>
                </Form>
              </Container>
            </React.Fragment>
        );
    }
}
