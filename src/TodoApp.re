open Utils;

open Types;

type state = list(item);

type action =
  | AddItem(string)
  | ToggleItem(int);

let component = ReasonReact.reducerComponent("TodoApp");

let lastId = ref(0);

let newItem = (~text as title) => {
  lastId := lastId^ + 1;
  {id: lastId^, title, completed: false}
};

let reducer = (action, items) =>
  switch action {
  | AddItem(text) => ReasonReact.Update([newItem(~text), ...items])
  | ToggleItem(id) =>
    let items =
      List.map((item) => item.id === id ? {...item, completed: ! item.completed} : item, items);
    ReasonReact.Update(items)
  };

let make = (_) => {
  ...component,
  initialState: () => [],
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
        (str("What to do"))
        <AddTodoField onSubmit=(reduce((text) => AddItem(text))) />
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
      <div className="footer"> (getFormattedNumberOfItems(numItems)) </div>
    </div>
  }
};