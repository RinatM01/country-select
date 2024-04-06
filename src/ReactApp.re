let countryUrl = "https://gist.githubusercontent.com/rusty-key/659db3f4566df459bd59c8a53dc9f71f/raw/4127f9550ef063121c564025f6d27dceeb279623/counties.json";
module App = {
  // This sample forces an import of Belt.*, so that CI builds can ensure that
  // Melange has been installed correctly for JS bundlers to be able to find it.
  [@react.component]
  let make = () => {
    let (countries, setCountries) = React.useState(_ => [||]);
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

    <div 
      style=(
        ReactDOM.Style.make(~width="200px", ~fontSize="16px", ())
      )>
      <h1>{React.string("Countries!")}</h1>
      <Select 
        options=countries
        isSearchable=true
        isClearable=true />
      // <ul>{countries
      //       -> Belt.Array.map(({label, value}) =>
      //             <li>{React.string(label ++ ": " ++ value)}</li>
      //           )
      //       -> React.array}
      // </ul>
    </div>;
  };
};

switch (ReactDOM.querySelector("#root")) {
| Some(element) =>
  let root = ReactDOM.Client.createRoot(element);
  ReactDOM.Client.render(root, <App />);
| None =>
  Js.Console.error("Failed to start React: couldn't find the #root element")
};
