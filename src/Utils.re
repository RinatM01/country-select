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


