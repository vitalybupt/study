import React, { Component } from 'react';
import PropTypes from "prop-types";
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

const Buttons = ({pages}) =>
      <React.Fragment>
        <ButtonGroup>
          <DropdownButton id="dropdown-basic" title={<span><i className="fa fa-file-text" aria-hidden="true"></i> Pages</span>} variant="secondary">
            { Object.keys(pages).map( page_id => (
                <Dropdown.Item href="#">{page_id}</Dropdown.Item>
            ) )}
          </DropdownButton>
          <Button variant="secondary"><i className="fa fa-refresh" aria-hidden="true"></i> Reload</Button>
          <Button variant="secondary"><i className="fa fa-plus-square" aria-hidden="true"></i> New Page</Button>
        </ButtonGroup>
          <Button variant="secondary" className="float-right"><i className="fa fa-trash" aria-hidden="true"></i> Delete Page</Button>
      </React.Fragment>;

Buttons.propTypes = {
    pages: PropTypes.object
};

{/*component of editor*/}
const Editor = ({markdown, handleInput}) =>
        <Form>
          <Form.Group>
            <Form.Label>Markdown</Form.Label>
            <Form.Control rows="25" as="textarea"
                          value={markdown} onChange={handleInput}></Form.Control>
          </Form.Group>
          <Form.Group>
            <Form.Label>Name</Form.Label>
            <Form.Control id="pageName" as="input" type="text"></Form.Control>
          </Form.Group>
        </Form>;

Editor.propTypes = {
    markdown : PropTypes.string,
    handleInput : PropTypes.func
};

const Wiki = ({pages, rendering, markdown, handleInput}) =>
      <React.Fragment>
        <Container>
          <Row>
            <Col>
              <Buttons pages={pages}/>
            </Col>
          </Row>
          <Row>
            <Col>{rendering}</Col>
            <Col>
              <Editor markdown={markdown} handleInput={handleInput}/>
              <Button variant="secondary"><i className="fa fa-pencil"
                                             aria-hidden="true"></i>Save</Button>
            </Col>
          </Row>
        </Container>
      </React.Fragment>;

export default class WikiContainer extends Component {
    
    state = { pages: {"editor":{"author":"a"}},
              markdown: ''};

    handleInput(value) {
        this.setState({markdown:value});
        console.log(this.state.markdown);
    }

    componentDidMount() {
        fetch('http://169.254.0.53:8080/api/pages')
            .then(response => response.json());
    };
  
    render() {
        Object.keys(this.state.pages).map( page_id => (console.log(page_id)));
	return <Wiki rendering={this.state.markdown} pages={this.state.pages}
                     handleInput={this.handleInput.bind(this)}/>;
    };
}
