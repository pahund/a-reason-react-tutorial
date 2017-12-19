let str = ReasonReact.stringToElement;

let getFormattedNumberOfItems = (numItems) =>
  str(string_of_int(numItems) ++ " item" ++ (numItems == 1 ? "" : "s"));

let valueFromEvent = (evt) : string => (
                                         evt
                                         |> ReactEventRe.Form.target
                                         |> ReactDOMRe.domElementToObj
                                       )##value;