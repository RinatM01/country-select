[@deriving (jsProperties, getSet)]
type t = {
    label: string,
    value: string
}

let decode = json =>
    Json.Decode.{
        label: json |> field("label", string),
        value: json |> field("value", string)
    };