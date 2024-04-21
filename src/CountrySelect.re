let countryUrl = "https://gist.githubusercontent.com/rusty-key/659db3f4566df459bd59c8a53dc9f71f/raw/4127f9550ef063121c564025f6d27dceeb279623/counties.json";

module Dropdown = {
    [@react.component]
    let make = (~children, ~target, ~isOpen, ~setIsOpen) => {

        let handleEsacepe = (e) => {
            e 
            |> React.Event.Keyboard.key 
            |> (fun
                | "Escape" => setIsOpen(_ => false)
                | _ => ()
            ); 
        };
        
        <div>
        target
        {isOpen 
            ? <div onKeyDown=handleEsacepe onBlur={_ => setIsOpen(_ => false)}> children </div>
            : React.null
        }
        
        </div>              
    };
}

[@react.component]
let make = (~country, ~onChange) => {
    let (countries, setCountries) = React.useState(_ => [||]);
    let (isOpen, setIsOpen) = React.useState(_=>false);
    let (countryLabel, setCountryLabel) = React.useState(_ => "");
    React.useEffect0(()=>{
      let _ =
        Js.Promise.(
          Fetch.fetch(countryUrl)
            |>then_(Fetch.Response.json)
            |>then_(json =>
              json
              ->Js.Json.decodeArray
              ->Belt.Option.getExn
              ->Belt.Array.map(Country.decode)
              ->resolve
            ) 
            |>then_(countries => setCountries(_ => countries) |> resolve)
        )
      Some(()=> ());
    });

    
    let stringValue = switch (country) {
        | None => ""
        | Some(countryStr) => countryStr 
    };

    let countryLabel = String.length(countryLabel) > 0 ? countryLabel : "Choose Country";
    

    <div>
        <Dropdown
            isOpen
            setIsOpen
            target={
                <button style=Styles.btn onClick={_=>setIsOpen(isOpen => !isOpen)} >
                    <Icon.Flag countryValue=stringValue isVisible=true /> 
                    <span style=Styles.label>{countryLabel -> React.string} </span>
                    <Icon.ArrowDown/>
                </button>
            }>
            <div style=Styles.selectWrapper(isOpen)>
                <Select
                    components={Select.Components.t(
                    ~indicatorsContainer=({innerRef, innerProps})=> <Custom.Indicator innerRef innerProps/>,
                    ~option={optionProps => <Custom.Option country optionProps />},
                    ~valueContainer={(props) => <Custom.ValueContainer props/>},
                    ()
                    )}
                    options=countries
                    menuIsOpen=isOpen
                    autoFocus=true
                    styles=Styles.styleOverrides
                    placeholder="Search"
                    onChange={(option : Js.Nullable.t(Country.t) )=> {
                        option 
                            |> Js.Nullable.toOption
                            |> Option.map(country => {
                                    setCountryLabel(_ => country |> Country.labelGet);
                                    country |> Country.valueGet
                                })
                            |> onChange;
                        setIsOpen(_ => false);
                    }}
                />
            </div>
        </Dropdown>
    </div>;
};