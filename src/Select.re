module StyleOverrides = {
  type styleInjector = ReactDOM.Style.t => ReactDOM.Style.t;

  [@deriving (jsProperties, getSet)]
  type t = {
    [@mel.optional]
    menu: option(styleInjector),
    [@mel.optional]
    control: option(styleInjector),
    [@mel.optional]
    container: option(styleInjector),
    [@mel.optional]
    placeholder: option(styleInjector)
  };
};

module Components = {

  [@deriving (jsProperties, getSet)]
  type componentsType = {
    [@mel.as "ValueContainer"]
    valueContainerComponent: React.component(Js.t({.}))
  };

  [@mel.module "react-select"]
  external components: componentsType = "components";

  type indicatorsContainerProps = {
    innerRef: ReactDOM.domRef,
    innerProps: Js.t({.}),
  };
  

  type optionProps = {
    data: Country.t,
    innerProps: Js.t({.}),
    isFocused: bool,
    isSelected: bool,
  };

  [@deriving (jsProperties, getSet)]
  type t = {
    [@mel.as "IndicatorsContainer"] [@mel.optional]
    indicatorsContainer: option(indicatorsContainerProps => React.element),
    [@mel.as "Option"] [@mel.optional]
    option: option(optionProps => React.element),
    [@mel.as "ValueContainer"] [@mel.optional]
    valueContainer: option(Js.t({.}) => React.element)
  };

};


[@mel.module "react-select"] [@react.component]
external make: (
  ~options: array('a),
  ~className: string=?,
  ~onChange: Js.nullable('a) => unit=?,
  ~onChange: Js.nullable('a)  => unit=?,
  ~closeMenuOnSelect: bool=?,
  ~components: Components.t=?,
  ~defaultValue: 'a=?,
  ~isLoading: bool=?,
  ~isOptionSelected: 'a => bool=?,
  ~menuIsOpen: bool=?,
  ~onChange: Js.Nullable.t('a) => unit=?,
  ~onKeyDown: React.Event.Keyboard.t => unit=?,
  ~ref: ReactDOM.Ref.t=?,
  ~placeholder: string=?,
  ~styles: StyleOverrides.t=?,
  ~autoFocus: bool=?
  ) => React.element = "default";
