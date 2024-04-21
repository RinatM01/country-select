let countryUrl = "https://gist.githubusercontent.com/rusty-key/659db3f4566df459bd59c8a53dc9f71f/raw/4127f9550ef063121c564025f6d27dceeb279623/counties.json";

module Dropdown = {
    open Utils.DomManipulations;
    [@react.component]
    let make = (~children, ~target, ~isOpen, ~setIsOpen, ~setIsFocused) => {

        let myRef = React.useRef(Js.Nullable.null);

        let closeMenu = () => {
            setIsOpen(_ => false);
            setIsFocused(_=>false);
        };
        
        // this handles the isFocused state just like normal select does
        React.useEffect0(()=>{
            let handleMouseDown = (e) => {
                let clickedObj = e |> React.Event.Keyboard.target;
                
                myRef.current
                |> Js.Nullable.toOption
                |> Option.map(myRef => {
                    !(myRef -> contains(clickedObj)) ? closeMenu(()) : ();
                    myRef
                })
                |> ignore;
                
            };
            document -> addEventListener("mousedown",handleMouseDown);
            Some(() => document -> removeEventListener("mousedown", handleMouseDown))
        });
        // event listener for keys that potentially open or close select menu
        let handleKeydown = (e) => {
            e 
            |> React.Event.Keyboard.key
            //|> Js.log
            |> (fun
                | "Escape" => setIsOpen(_ => false)
                | " " => {
                    e |> React.Event.Keyboard.stopPropagation;
                    setIsFocused(isFocused => {
                        setIsOpen(isOpen => !isOpen && isFocused);
                        isFocused
                    });
                }
                | "Enter" => setIsFocused(isFocused => {
                    setIsOpen(isOpen => !isOpen && isFocused);
                    isFocused
                })
                | _ => ()
            ); 
        };

        React.useEffect0(()=> {
            document -> addEventListener("keydown", handleKeydown);
            Some(()=> document -> removeEventListener("keydown", handleKeydown))
        });

        
        
        <div ref={myRef -> ReactDOM.Ref.domRef} >
        target
        {isOpen 
            ? <div 
                > children </div>
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
    let (isFocused, setIsFocused) = React.useState(_=>false);
    

    <div>
        <Dropdown
            isOpen
            setIsOpen
            setIsFocused
            target={
                <button 
                    style=Styles.btn(isFocused) 
                    onClick={_=>{
                        setIsOpen(isOpen => !isOpen);
                        setIsFocused(_ => true);
                    }} 
                >
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
                    onKeyDown={e => {
                        //prevents from menu being open, cause the "Enter" can also be picked up by dropdown
                        e |> React.Event.Keyboard.stopPropagation;
                        e
                        |> React.Event.Keyboard.key
                        |> (fun
                            | "Escape"
                            | "Enter" => setIsOpen(_ => false)
                            | _ => ()
                        )
                    }}
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