open Utils;

module Option = {
    [@react.component]
    let make =
      (
        ~country,
        ~optionProps as
          {
            data: {label, value},
            innerProps,
            isFocused,
            isSelected:_,
          }:
            Select.Components.optionProps,
      ) => {
    let isSelected = switch (country) {
        | None => false
        | Some(countryVal) => countryVal == value
    };

    

    let (isVisible, setIsVisible) = React.useState(_=>false);
    let optionRef = React.useRef(Js.Nullable.null);
    let observerRef = React.useRef(None);

    // This logic makes it so that flags only render when they are visible
    React.useEffect0(()=>{
            observerRef.current = Some(IntersectionOberserver.make((entries) => 
                                                entries |> Array.fold_left((_, entry) => setIsVisible(_=>entry -> IntersectionOberserver.isInersecting),())));
            Some(()=>());
        });

    React.useEffect1(()=>{
         optionRef.current
                |> Js.Nullable.toOption
                |> Option.map(myRef => {
                    myRef |> IntersectionOberserver.observe(observerRef.current |> Option.get);
                    myRef
                })
                |> ignore;
        Some(()=> observerRef.current |> Option.get |> IntersectionOberserver.disconnect);
    }, [|optionRef|]);

    React.useEffect2(()=> {
        isFocused 
        ?  optionRef.current
            |> Js.Nullable.toOption
            |> Option.map(myRef => {
                myRef -> ScrollIfNeeded.scrollIntoView(ScrollIfNeeded.options(
                    ~scrollMode= "if-needed",
                    ~block= "nearest",
                    ~inline= "nearest",
                    ~behavior= "smooth",
                    ()
                ));
                myRef
            })
            |> ignore
        : ();
        Some(()=>());
    },(isFocused, optionRef));

    <Spread props=innerProps>
        <div ref={ReactDOM.Ref.domRef(optionRef)} style=Styles.optionWrapper(~isSelected, ~isFocused)>
            <div style=Styles.flagLabel>
                <Icon.Flag countryValue=value isVisible />
                <div> {React.string(label)} </div>
            </div>
            <div style=Styles.trafficLabel> {React.string("0.0K")} </div>
        </div>
    </Spread>;
    };
};

module Indicator = {
    [@react.component]
    let make = (~innerRef, ~innerProps) =>
        <Spread props=innerProps>
            <span ref=innerRef/>
        </Spread>;
}

module ValueContainer = {
    [@react.component]
    let make = ( ~props) => {
        <div style=Styles.valueContainerWrapper>
            <Icon.Search/>
            {React.createElement(
                Select.Components.components.valueContainerComponent,
                props,
            )}
        </div>;
    };
};
