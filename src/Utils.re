module Spread = {
  [@react.component]
  let make = (~props, ~children) => React.cloneElement(children, props);
};

module IntersectionOberserver = {
    type intersectionObserverEntry;
    type intersectionObserver;
    [@mel.get] 
    external isInersecting: intersectionObserverEntry => bool = "isIntersecting";
    [@mel.new]
    external make: (array(intersectionObserverEntry) => unit) => intersectionObserver = "IntersectionObserver";
    [@mel.send] external disconnect: intersectionObserver => unit = "disconnect";
    [@mel.send] external observe: (intersectionObserver, Dom.element) => unit = "observe";
    
}
module DomManipulations = {
    type document;
    external document: document = "document";

    //unfortunately I had set the second argument to be js object
    //even though we know it must be Dom.element, because 
    //React.Event.Keyboard.target returns js object
    [@mel.send] 
    external contains: (Dom.element, Js.t({..})) => bool = "contains";
    [@mel.send]
    external addEventListener: (document, string, (React.Event.Keyboard.t => unit)) 
    => unit = "addEventListener";

    [@mel.send]
    external removeEventListener: (document, string, (React.Event.Keyboard.t => unit)) 
    => unit = "removeEventListener";
}


module ScrollIfNeeded = {
    [@deriving jsProperties]
    type options = {
        [@mel.optional]
        scrollMode: option(string),
        [@mel.optional]
        block: option(string),
        [@mel.optional]
        inline: option(string),
        [@mel.optional]
        behavior: option(string)
    };
    [@mel.module "scroll-into-view-if-needed"]
    external scrollIntoView: (Dom.element, options) => unit = "default";

}


