[@mel.module "react-select"] [@react.component]
external make: (
        ~options: array('a),
        ~className: string=?,
        ~style: ReactDOM.Style.t=?,
        ~onChange: Js.nullable('a) => unit=?,
        ~onChange: Js.nullable('a)  => unit=?,
        ~loadOptions: string => Js.Promise.t('a)=?,
        ~isClearable: bool=?,
        ~isSearchable: bool=?
    ) => React.element = "default";
