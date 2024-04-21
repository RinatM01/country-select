let countryUrl = "https://gist.githubusercontent.com/rusty-key/659db3f4566df459bd59c8a53dc9f71f/raw/4127f9550ef063121c564025f6d27dceeb279623/counties.json";
module App = {
  // This sample forces an import of Belt.*, so that CI builds can ensure that
  // Melange has been installed correctly for JS bundlers to be able to find it.
  
  
  [@react.component]
  let make = () => {
    let (country, setCountry) = React.useState(() => None);
    <div>
      <CountrySelect
        country
        onChange={country => setCountry(_ => country)}
      />
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
