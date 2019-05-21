import React from 'react';
import {BrowserRouter as Router, Route} from 'react-router-dom';
import './App.css';

import routes from './routes';

export default () => {
    return (
	<Router>
	<div>
	{
	    routes.map((route, index) => {
		return <Route key={index} exact path={route.path} component={route.component}/>;
	    })
	}
	</div>
	</Router>
    );
};
