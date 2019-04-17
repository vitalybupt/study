import React, { Component } from 'react';
import DropdownButton from 'react-bootstrap/DropdownButton';
import Dropdown from 'react-bootstrap/Dropdown';
import Button from 'react-bootstrap/Button';
import ButtonToolbar from 'react-bootstrap/ButtonToolbar';
import ButtonGroup from 'react-bootstrap/ButtonGroup';

import "popper.js/dist/popper.min.js";
import "bootstrap/dist/css/bootstrap.min.css";
import "font-awesome/css/font-awesome.css";

const Buttons = props =>
      <React.Fragment>
        <ButtonGroup>
          <DropdownButton id="dropdown-basic" title={<span><i class="fa fa-file-text" aria-hidden="true"></i> Pages</span>} variant="secondary">
            <Dropdown.Item href="#">page </Dropdown.Item>
          </DropdownButton>
          <ButtonGroup className="mr-2 float-right">
            <Button variant="secondary"><i class="fa fa-refresh" aria-hidden="true"></i> Reload</Button>
            <Button variant="secondary"><i class="fa fa-plus-square" aria-hidden="true"></i> New Page</Button>
            <Button variant="secondary" className="float-right"><i class="fa fa-trash" aria-hidden="true"></i> Delete Page</Button>
          </ButtonGroup>
        </ButtonGroup>
      </React.Fragment>;

{/*component of editor*/}
const Editor = props =>
      <React.Fragment>
                  <form>
                    <div className="form-group">
                      <label for="markdown">Markdown</label>
                      <textarea id="markdown" class="form-control" rows="25"></textarea>
                    </div>
                    <div class="form-group">
                      <label for="pageName">Name</label>
                      <input class="form-control" type="text" value="" id="pageName" ng-model="pageName" ng-disabled="pageExists"/>
                    </div>
                    <button type="button" class="btn btn-secondary"><i class="fa fa-pencil"
                                                                       aria-hidden="true"></i> Save
                    </button>
                  </form>
      </React.Fragment>;


export default class Wiki extends Component {
    render() {
	return (
            <div class="container">
              <div class="row">
                <div class="col-md-12">
                  <Buttons/>
                </div>
            </div>
              <div class="row">
                <div class="col-md-6" id="rendering"></div>
                <div class="col-md-6">
                  <Editor/>
                </div>
              </div>
            </div>
        );
    };
}
