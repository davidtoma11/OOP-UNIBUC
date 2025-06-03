# BOOKSTER - Library Management System

## Key Concepts & Architecture
Demonstrates core OOP principles through a robust library management system.

### OOP Implementation
#### Encapsulation
- Private fields with controlled access (e.g. `User.getEmail()`)
- Secure credential handling in authentication

#### Inheritance
- `Person` → `User`/`Admin` hierarchies
- Role-specific functionality extension

#### Polymorphism
- Overridden `toString()` for all entities
- Dynamic menu rendering based on user type

#### Singleton
- `DataInitialization` for centralized DB access
- `AuditService` for system-wide logging

## Core Functionalities

| Feature            | User Functions               | Admin Functions              | OOP Principle         |
|--------------------|------------------------------|------------------------------|-----------------------|
| Account Management | View profile                 | CRUD all user accounts       | Inheritance           |
| Book Operations    | Browse available books       | Add/edit/remove books        | Encapsulation         |
| Order System       | Place/cancel/return orders   | Manage all system orders     | Polymorphism          |
| Review System      | Write/submit reviews         | Moderate/remove reviews      | Singleton             |

## Advanced Features
- **Role-Based Access Control**
  - Secure authentication with password hashing
  - Separate UI flows for Users/Admins

- **Data Persistence**
  - JDBC with prepared statements
  - Configuration via `db.properties`

- **Transaction System**
  - Borrow/return with status tracking
  - Rating validation (1-5 stars)

- **Audit Trail**
  - Immutable logs of all critical actions
  - Timestamped operations tracking
