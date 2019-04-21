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
            { Object.keys(pages).map( (page_id, i) => (
                <Dropdown.Item key={i} href="#">{page_id}</Dropdown.Item>
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

const Wiki = ({pages, preview, markdown, handleInput}) =>
      <React.Fragment>
        <Container>
          <Row>
            <Col>
              <Buttons pages={pages}/>
            </Col>
          </Row>
          <Row>
            <Col><div dangerouslySetInnerHTML={{__html : preview}}/></Col>
            <Col>
              <Editor markdown={markdown} handleInput={handleInput}/>
              <Button variant="secondary"><i className="fa fa-pencil"
                                             aria-hidden="true"></i>Save</Button>
            </Col>
          </Row>
        </Container>
      </React.Fragment>;

Wiki.propTypes = {
    pages : PropTypes.object,
    markdown : PropTypes.string,
    handleInput : PropTypes.func
}

export default class WikiContainer extends Component {
    markdownRenderingPromise = null;
    
    state = {
        pages: {},
        markdown: '',
        preview : ''
    };
    
    handleInput(value) {
        this.setState({markdown:value.target.value});

        if (this.markdownRenderingPromise !== null) {
            clearTimeout(this.markdownRenderingPromise);  // <3>
        };

        this.markdownRenderingPromise = setTimeout(function() {
            this.markdownRenderingPromise = null;
            console.log(this.state.markdown);
            fetch('http://192.168.56.101:8080/app/markdown', {
                method: 'POST',
                body : this.state.markdown
            })
                .then(response => response.text())
                .then(data => this.setState({preview : data}));
        }.bind(this), 300);
    }

    componentDidMount() {
        fetch('http://192.168.56.101:8080/api/pages')
            .then(response => response.json())
            .then(data => this.setState({pages : data}));
    };
  
    render() {
	return <Wiki preview={this.state.preview} pages={this.state.pages}
                     handleInput={this.handleInput.bind(this)}/>;
    };
}
