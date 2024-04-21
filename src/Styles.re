open ReactDOM.Style;
let styleOverrides = Select.StyleOverrides.t(
    ~menu=
        style =>
            combine(
                style,
                make(
                    ~marginTop= "0px",
                    ~borderTop="none",
                    ~borderRadius= "0px 0px 3px 3px",
                    (),
                ),
            ),
    ~control=
        style =>
            combine(
                style,
                make(
                    ~borderRadius= "3px 3px 0px 0px",
                    ~border="0",
                    ~fontFamily="Arial",
                    ~boxShadow="none",
                    ()
                    )
            ),
    ~container=
        style=>
            combine(
                style,
                make(
                    ~borderRadius= "3px",
                    ~boxShadow= "0px 0px 0px 1px rgba(0, 0, 0, 0.08), 0px 3px 18px rgba(0, 0, 0, 0.15)",
                    ~position="absolute",
                    ~width="230px",
                    ~top="2px",
                    ()
                )
            ),
    ~placeholder=
        style =>
            combine(
                style,
                make(
                    ~fontFamily= "Arial",
                    ~fontSize="14px",
                    ~color="rgba(0,0,0,0.32)",
                    ()
                    )
            ),
    ()
);
let btn = make(~backgroundColor="white",
                ~border="1px solid rgba(0,0,0,0.2)",
                ~padding="7px 9px",
                ~borderRadius="3px",
                ~cursor="pointer",
                ~width="auto",
                ());
let label = make(~marginRight="7px",());
let selectWrapper = (isOpen) => make(~width="230px",
                                    ~display= isOpen ? "block" : "none",
                                    ~position="relative",
                                    ());

let optionWrapper = (~isSelected, ~isFocused) => make(~display="flex",
                                                    ~padding="4px 10px",
                                                    ~fontFamily="Arial",
                                                    ~justifyContent="space-between",
                                                    ~alignItems="center",
                                                    ~backgroundColor= isSelected ? "rgba(255, 219, 179, 1)" : isFocused ? "rgba(255, 219, 179, 0.5)" : "rgba(0,0,0,0)",
                                                    ());
let flagLabel = make(~display="flex",~alignItems="center", ~fontSize="14px", ());
let trafficLabel = make(~color="rgba(0,0,0,0.52)", ~fontSize="12px", ());
let valueContainerWrapper = make(~display="flex",
                                ~alignItems="center",
                                ());
let flagIcon = make(~width="14px", ~height="14px", ~marginRight="9px", ());
let searchIcon = make(~marginLeft="11px",());