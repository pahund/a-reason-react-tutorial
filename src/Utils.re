let str = ReasonReact.stringToElement;
let getFormattedNumberOfItems = numItems =>
  str(string_of_int(numItems) ++ " item" ++ (numItems == 1 ? "": "s"));
