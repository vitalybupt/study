import React, { Component } from 'react';
import DropdownButton from 'react-bootstrap/DropdownButton';
import Dropdown from 'react-bootstrap/Dropdown';
import Button from 'react-bootstrap/Button';
import ButtonGroup from 'react-bootstrap/ButtonGroup';
import Form from 'react-bootstrap/Form';
import Container from 'react-bootstrap/Container';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';

import "popper.js/dist/popper.min.js";
import "bootstrap/dist/css/bootstrap.min.css";
import "font-awesome/css/font-awesome.css";

const Buttons = props =>
      <React.Fragment>
        <ButtonGroup>
          <DropdownButton id="dropdown-basic" title={<span><i class="fa fa-file-text" aria-hidden="true"></i> Pages</span>} variant="secondary">
            <Dropdown.Item href="#">page </Dropdown.Item>
          </DropdownButton>
          <Button variant="secondary"><i class="fa fa-refresh" aria-hidden="true"></i> Reload</Button>
          <Button variant="secondary"><i class="fa fa-plus-square" aria-hidden="true"></i> New Page</Button>
        </ButtonGroup>
          <Button variant="secondary" className="float-right"><i class="fa fa-trash" aria-hidden="true"></i> Delete Page</Button>
      </React.Fragment>;

{/*component of editor*/}
const Editor = props =>
        <Form>
          <Form.Group>
            <Form.Label>Markdown</Form.Label>
            <Form.Control rows="25" as="textarea"></Form.Control>
          </Form.Group>
          <Form.Group>
            <Form.Label>Name</Form.Label>
            <Form.Control id="pageName" as="input" type="text"></Form.Control>
          </Form.Group>
        </Form>;

const Wiki = props =>
      <React.Fragment>
        <Buttons/>
        <Container>
          <Row>
            <Col></Col>
            <Col>
              <Editor/>
              <Button variant="secondary"><i className="fa fa-pencil"
                                             aria-hidden="true"></i>Save</Button>
            </Col>
          </Row>
        </Container>
      </React.Fragment>;

export default class WikiContainer extends Component {
    render() {
	return <Wiki/>;
    };
}
