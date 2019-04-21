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

const Buttons = ({pages, handleLoadPage, handleLoadPages, handleNewPage}) =>
      <React.Fragment>
        <ButtonGroup>
          <DropdownButton id="dropdown-basic" title={<span><i className="fa fa-file-text" aria-hidden="true"></i> Pages</span>} variant="secondary">
            { pages.map( (page, i) => (
                <Dropdown.Item key={i} href="#" onClick={()=>handleLoadPage(page.id)}>{page.name}</Dropdown.Item>
            ) )}
          </DropdownButton>
          <Button variant="secondary"><i className="fa fa-refresh" aria-hidden="true" onClick={()=>handleLoadPages()}></i> Reload</Button>
          <Button variant="secondary"><i className="fa fa-plus-square" aria-hidden="true" onClick={()=>handleNewPage()}></i> New Page</Button>
        </ButtonGroup>
          <Button variant="secondary" className="float-right"><i className="fa fa-trash" aria-hidden="true"></i> Delete Page</Button>
      </React.Fragment>;

Buttons.propTypes = {
    pages: PropTypes.array,
    handleLoadPage : PropTypes.func,
    handleLoadPages : PropTypes.func,
    handleNewPage : PropTypes.func,
};

{/*component of editor*/}
const Editor = ({pageName, markDown, handleInput}) =>
        <Form>
          <Form.Group>
            <Form.Label>Markdown</Form.Label>
            <Form.Control rows="25" as="textarea"
                          value={markDown} onChange={handleInput}></Form.Control>
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

const Wiki = ({pages, handleLoadPage, handleLoadPages, handleNewPage, preview, markdown, handleInput}) =>
      <React.Fragment>
        <Container>
          <Row>
            <Col>
              <Buttons pages={pages} handleLoadPage={handleLoadPage} handleLoadPages={handleLoadPages} handleNewPage={handleNewPage}/>
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
    pages : PropTypes.array,
    handleLoadPage : PropTypes.func,
    handleLoadPages : PropTypes.func,
    handleNewPage : PropTypes.func,
    
    markdown : PropTypes.string,
    handleInput : PropTypes.func
}

export default class WikiContainer extends Component {
    markdownRenderingPromise = null;
    DEFAULT_PAGENAME = "Example page";
    DEFAULT_MARKDOWN = "# Example page\n\nSome text _here_.\n";

    state = {
        currentPage: {
            id:undefined,
            name : this.DEFAULT_PAGENAME,
            markdown : this.DEFAULT_MARKDOWN
        },
        pages: [],
        preview : ''
    };
    
    handleInput(value) {
        this.setState({
            currentPage: {
                ...this.state.currentpage,
                markdown : value.target.value,
            }
        });

        if (this.markdownRenderingPromise !== null) {
            clearTimeout(this.markdownRenderingPromise);  // <3>
        };

        this.markdownRenderingPromise = setTimeout(function() {
            this.markdownRenderingPromise = null;
            console.log(this.state.currentPage.markdown);
            fetch('http://192.168.56.101:8080/app/markdown', {
                method: 'POST',
                body : this.state.currentPage.markdown
            })
                .then(response => response.text())
                .then(data => this.setState({preview : data}));
        }.bind(this), 300);
    };

    loadPage(pageId) {
        console.log("load page:", pageId);
        fetch("http://192.168.56.101:8080/api/pages/" + pageId)
            .then(function(response) {
                if (!response.ok) {
                    throw Error(response.statusText);
                };
                return response;
            })
            .then(response => response.json())
            .then(data =>{
                this.setState({preview : data.html, markdown : data.markdown});
            })
            .catch( error => console.log(error, "when loading page:",pageId));
    };

    loadPages() {
        console.log("load pages");
        fetch('http://192.168.56.101:8080/api/pages')
            .then(function(response){
                if(!response.ok){
                    throw Error(response.statueText);
                };
                return response;
            })
            .then(response => response.json())
            .then( data => this.setState({pages : data.pages}))
            .catch(error => console.log(error));
    };

    newPage() {
        this.setState({
            currentPage : {
                id:undefined,
                name : this.DEFAULT_PAGENAME,
                markdown : this.DEFAULT_MARKDOWN
            },
            preview : ''
        });
        console.log("enter newpage", this.state.currentPage);
    };
    
    componentDidMount() {
        this.loadPages();
    };
  
    render() {
	return <Wiki pages={this.state.pages} handleLoadPage={this.loadPage.bind(this)} handleLoadPages={this.loadPages.bind(this)} handleNewPage={this.newPage.bind(this)}
                     preview={this.state.preview} markdown={this.state.currentPage.markdown} handleInput={this.handleInput.bind(this)}/>;
    };
}
