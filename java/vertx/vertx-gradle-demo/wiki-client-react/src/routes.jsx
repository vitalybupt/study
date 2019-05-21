import React from "react";
import {Redirect} from "react-router-dom"

import WikiContainer from "./Wiki";
import Login from "./Login";

export default [
    {
	path: "/",
	component: ()=><Redirect to ='/wiki'/>
    },
    {
	path: "/wiki",
	component: WikiContainer
    },
    {
	path: "/login",
	component: Login
    }
];

