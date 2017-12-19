type item = {
  id: int,
  title: string,
  completed: bool
};

type state = list(item);

type action =
  | AddItem(string)
  | ToggleItem(int);

let component = ReasonReact.reducerComponent("TodoApp");

let lastId = ref(0);

let newItem = (~text as title) => {
  lastId := lastId^ + 1;
  {id: lastId^, title, completed: true}
};

module TodoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let getClassName = ({completed}) => "item" ++ (completed ? " completed" : "");
  let make = (~item, ~onToggle, _) => {
    ...component,
    render: (_) =>
      <div className=(getClassName(item))>
        <input
          _type="checkbox"
          onChange=((_) => onToggle())
          checked=(Js.Boolean.to_js_boolean(item.completed))
        />
        (Utils.str(item.title))
      </div>
  };
};

module Input = {
  type state = string;
  let component = ReasonReact.reducerComponent("Input");
  let make = (~onSubmit, _) => {
    ...component,
    initialState: () => "",
    reducer: (newText, _text) => ReasonReact.Update(newText),
    render: ({state: text, reduce}) =>
      <input
        value=text
        _type="text"
        placeholder="Write something to do"
        onChange=(reduce((evt) => Utils.valueFromEvent(evt)))
        onKeyDown=(
          (evt) =>
            if (ReactEventRe.Keyboard.key(evt) == "Enter") {
              onSubmit(text);
              (reduce(() => ""))()
            }
        )
      />
  };
};

let make = (_) => {
  ...component,
  initialState: () => [{id: 0, title: "Write some things to", completed: false}],
  reducer: (action, items) =>
    switch action {
    | AddItem(text) => ReasonReact.Update([newItem(~text), ...items])
    | ToggleItem(id) =>
      let items =
        List.map((item) => item.id === id ? {...item, completed: ! item.completed} : item, items);
      ReasonReact.Update(items)
    },
  render: ({state: items, reduce}) => {
    let numItems = List.length(items);
    <div className="app">
      <div className="title">
        (Utils.str("What to do"))
        <Input onSubmit=(reduce((text) => AddItem(text))) />
      </div>
      <div className="items">
        (
          List.map(
            (item) =>
              <TodoItem
                key=(string_of_int(item.id))
                onToggle=(reduce(() => ToggleItem(item.id)))
                item
              />,
            items
          )
          |> Array.of_list
          |> ReasonReact.arrayToElement
        )
      </div>
      <div className="footer"> (Utils.getFormattedNumberOfItems(numItems)) </div>
    </div>
  }
};